import React from 'react';
import { connect } from 'react-redux';
import { PageHeader } from 'antd';
import NamespaceList from '../components/namespace_list';
import NamespaceAddButton from '../components/namespace_add';
import NamespaceSelecter from '../components/namespace_selector.js';

class Page extends React.PureComponent {

    render() {
        return (
            <div>
                <PageHeader title="命名空间" extra={[
                    <span key="selector"><NamespaceSelecter /></span>,
                    <NamespaceAddButton />
                ]}>
                </PageHeader>

                <NamespaceList />
            </div>
        );
    }
}

export default connect()(Page);
