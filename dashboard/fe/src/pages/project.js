import React from 'react';
import { connect } from 'react-redux';
import { PageHeader, Row, Col } from 'antd';
import RepoList from '../components/func_repo_list';

class Page extends React.PureComponent {

    constructor(props) {
        super(props);
    }

    render() {
        return (
            <div>
                <PageHeader title="项目" />

                <RepoList />
            </div>
        );
    }
}

export default connect()(Page);
