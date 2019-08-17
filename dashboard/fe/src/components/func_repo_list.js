import React from 'react';
import { Table, Tag } from 'antd';
import { connect } from 'react-redux';
import {
    fetchFuncRepoList,
    FUNC_REPO_LIST_UNSET,
} from '../actions/repo';

class FuncRepoList extends React.PureComponent {

    constructor(props) {
        super(props);

        if (this.props.repo.state === FUNC_REPO_LIST_UNSET) {
            this.props.dispatch(fetchFuncRepoList());
        }
    }

    render() {
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
                    </div>
                )
            }
        ];

        let dataSource = [];
        if (this.props.repo.repo.map(n => dataSource.push({
            key: n.name,
            repoName: n.name,
            repoVersions: n.versions
        })))
        
        return (<Table columns={COLUMNS} dataSource={dataSource} />);
    }
};

export default connect(({ repo }) => ({
    repo: repo.funcRepo
}))(FuncRepoList);


