import React from 'react';
import { Table, Tag, Button } from 'antd';
import { connect } from 'react-redux';
import {
    deleteRepo,
    fetchFuncRepoList,
    FUNC_REPO_LIST_UNSET,
} from '../actions/repo';

class FuncRepoList extends React.PureComponent {

    state = {
        waitingFresh: false
    };

    FRESH_INTERVAL = 1000;

    constructor(props) {
        super(props);

        if (this.props.repo.state === FUNC_REPO_LIST_UNSET) {
            this.props.dispatch(fetchFuncRepoList());
        }
    }

    render() {
        if (this.state.waitingFresh === false) {
            this.setState({ waitingFresh: true }); // TODO
            setTimeout(() => {
                this.props.dispatch(fetchFuncRepoList());
                this.setState({ waitingFresh: false });
            }, this.FRESH_INTERVAL);
        };

        const COLUMNS = [
            {
                title: '函数名称',
                dataIndex: 'repoName',
                key: 'repoName'
            },
            {
                title: '版本',
                key: 'repoVersions',
                render: n => (<div>{n.repoVersions.map(v => <Tag key={v}>{v}</Tag>)}</div>)
            },
            {
                title: '操作',
                key: 'operation',
                render: n => (
                    <div>
                        <Button
                            onClick={() => {
                                if (n.repoVersions.length === 1) {
                                    this.props.dispatch(deleteRepo(n.repoName, n.repoVersions[0]));
                                }
                                else {
                                    console.log("multi");
                                }
                            }}
                            size="small">
                            删除
                        </Button>
                    </div>
                )
            }
        ];

        let dataSource = [];
        this.props.repo.repo.filter(n => n.name !== '<none>').map(n => dataSource.push({
            key: n.name,
            repoName: n.name,
            repoVersions: n.versions
        }))
        
        return (<Table columns={COLUMNS} dataSource={dataSource} />);
    }
};

export default connect(({ repo }) => ({
    repo: repo.funcRepo
}))(FuncRepoList);


